#ifndef CTHULHU_EPETRACOMM_HPP
#define CTHULHU_EPETRACOMM_HPP

#include <Teuchos_Comm.hpp>
#include <Teuchos_DefaultMpiComm.hpp>
#include <Teuchos_DefaultSerialComm.hpp>

#include <Epetra_Comm.h>
#include <Epetra_MpiComm.h>
#include <Epetra_SerialComm.h>

// Convert a Teuchos_Comm into a Epetra_Comm.
// (needed for EpetraMap constructor)

// JG Note: At present, there is no support for Epetra_MpiSmpComm but if
// needed, Cthulhu object XXX with such internal Comm can be created
// using the constructor Cthulhu::EpetraXXX(myEpetra_Map) which
// directly wrap an Epetra_XXX.

// JG TODO: replace MPI_COMM_WORLD
// JG TODO getRawMpiComm()

const Teuchos::RCP<const Epetra_Comm> Teuchos_Comm2Epetra_Comm(const Teuchos::RCP< const Teuchos::Comm< int > > & comm) {

  if (Teuchos::rcp_dynamic_cast<const Teuchos::MpiComm< int > >(comm)  != Teuchos::null) // JG TODO: & ?
    return Teuchos::rcp(new Epetra_MpiComm(MPI_COMM_WORLD)); // At present, the only MPI communicator in Teuchos is MPI_COMM_WORLD. 

  else if ((Teuchos::rcp_dynamic_cast<const Teuchos::SerialComm< int > >(comm)  != Teuchos::null))
    return Teuchos::rcp(new Epetra_SerialComm());

  else 
    return Teuchos::null;

}

const Teuchos::RCP< const Teuchos::Comm< int > > Epetra_Comm2Teuchos_Comm(Teuchos::RCP<const Epetra_Comm> & comm) {

  if (Teuchos::rcp_dynamic_cast<const Epetra_MpiComm>(comm) != Teuchos::null)
    return Teuchos::rcp(new Teuchos::MpiComm<int>(Teuchos::opaqueWrapper(MPI_COMM_WORLD))); // At present, the only MPI communicator in Teuchos is MPI_COMM_WORLD. 
  else if (Teuchos::rcp_dynamic_cast<const Epetra_SerialComm>(comm) != Teuchos::null)
    return Teuchos::rcp(new Teuchos::SerialComm<int>());

  else
    return Teuchos::null;
}

#endif // CTHULHU_EPETRACOMM_HPP
